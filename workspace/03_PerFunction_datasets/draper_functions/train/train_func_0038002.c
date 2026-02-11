notify (xlator_t *this, int32_t event, void *data, ...)
{
        stripe_private_t *priv = NULL;
        int               down_client = 0;
        int               i = 0;
        gf_boolean_t      heard_from_all_children = _gf_false;

        if (!this)
                return 0;

        priv = this->private;
        if (!priv)
                return 0;

        switch (event)
        {
        case GF_EVENT_CHILD_UP:
        {

                for (i = 0; i < priv->child_count; i++) {
                        if (data == priv->xl_array[i])
                                break;
                }

                if (priv->child_count == i) {
                        gf_log (this->name, GF_LOG_ERROR,
                                "got GF_EVENT_CHILD_UP bad subvolume %s",
                                data? ((xlator_t *)data)->name: NULL);
                        break;
                }

                LOCK (&priv->lock);
                {
                        if (data == FIRST_CHILD (this))
                                priv->first_child_down = 0;
                        priv->last_event[i] = event;
                }
                UNLOCK (&priv->lock);
        }
        break;
        case GF_EVENT_CHILD_CONNECTING:
        {

                goto out;
        }
        case GF_EVENT_CHILD_DOWN:
        {

                for (i = 0; i < priv->child_count; i++) {
                        if (data == priv->xl_array[i])
                                break;
                }

                if (priv->child_count == i) {
                        gf_log (this->name, GF_LOG_ERROR,
                                "got GF_EVENT_CHILD_DOWN bad subvolume %s",
                                data? ((xlator_t *)data)->name: NULL);
                        break;
                }

                LOCK (&priv->lock);
                {
                        if (data == FIRST_CHILD (this))
                                priv->first_child_down = 1;
                        priv->last_event[i] = event;
                }
                UNLOCK (&priv->lock);
        }
        break;

        default:
        {

                default_notify (this, event, data);
                goto out;
        }
        break;
        }


        for (i = 0, down_client = 0; i < priv->child_count; i++)
                if (priv->last_event[i] != GF_EVENT_CHILD_UP)
                        down_client++;

        LOCK (&priv->lock);
        {
                priv->nodes_down = down_client;
        }
        UNLOCK (&priv->lock);

        heard_from_all_children = _gf_true;
        for (i = 0; i < priv->child_count; i++)
                if (!priv->last_event[i])
                        heard_from_all_children = _gf_false;

        if (heard_from_all_children)
                default_notify (this, event, data);
out:
        return 0;
}
