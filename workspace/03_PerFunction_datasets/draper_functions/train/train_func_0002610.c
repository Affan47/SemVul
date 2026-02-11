request_is_complete (TpProxy *self,
    TpProxyPrepareRequest *req)
{
  guint i;
  gboolean complete = TRUE;

  for (i = 0; i < req->features->len; i++)
    {
      GQuark feature = g_array_index (req->features, GQuark, i);
      FeatureState state = tp_proxy_get_feature_state (self, feature);
      const TpProxyFeature *feat_struct = tp_proxy_subclass_get_feature (
          G_OBJECT_TYPE (self), feature);

      switch (state)
        {
          case FEATURE_STATE_UNWANTED:


            g_assert (req->core);
            complete = FALSE;


          case FEATURE_STATE_WANTED:
            if (core_prepared (self) ||
                req->core)
              {
                gboolean failed;


                if (!check_feature_interfaces (self, feature))
                  {
                    if (TP_IS_CONNECTION (self) &&
                        tp_connection_get_status ((TpConnection *) self, NULL)
                        != TP_CONNECTION_STATUS_CONNECTED)
                      {


                        tp_proxy_set_feature_state (self, feature,
                            FEATURE_STATE_MISSING_IFACE);
                      }
                    else
                      {
                        tp_proxy_set_feature_state (self, feature,
                            FEATURE_STATE_FAILED);
                      }
                    continue;
                  }

                if (check_depends_ready (self, feature, FALSE, &failed))
                  {

                    DEBUG ("%p: calling callback for %s", self,
                        g_quark_to_string (feature));

                    tp_proxy_set_feature_state (self, feature,
                        FEATURE_STATE_TRYING);

                    prepare_feature (self, feat_struct);
                    complete = FALSE;
                  }
                else if (failed)
                  {
                    tp_proxy_set_feature_state (self, feature,
                        FEATURE_STATE_FAILED);
                  }
                else
                  {


                    complete = FALSE;
                  }
              }
            break;

          case FEATURE_STATE_TRYING:
            complete = FALSE;
            break;

          case FEATURE_STATE_INVALID:
          case FEATURE_STATE_FAILED:
          case FEATURE_STATE_MISSING_IFACE:
          case FEATURE_STATE_READY:

            break;
        }
    }

  return complete;
}
