listener_unref (Listener* l)
{
  l->refcount -= 1;
  if (l->refcount == 0)
    {
      (*l->destroy_notify)(l->listener_data);
      g_free(l);
    }
}
