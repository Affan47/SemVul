_on_child_resize(void *data, Evas *evas __UNUSED__, Evas_Object *o __UNUSED__, void *einfo __UNUSED__)
{
   Evas_Object *box = data;
   EVAS_OBJECT_BOX_DATA_GET_OR_RETURN(box, priv);
   if (!priv->layouting) evas_object_smart_changed(box);
}
