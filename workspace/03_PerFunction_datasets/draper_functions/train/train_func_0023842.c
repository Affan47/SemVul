vink_epp_check (struct vink_client *client, int type,
                const char **objects, size_t count)
{
  struct vink_epp_state *state;
  struct VINK_buffer query;
  int result;
  size_t i;
  char trid[32];

  state = vink_client_state (client);

  ARRAY_INIT (&query);

  epp_gen_trid (trid);

  if (-1 == VINK_buffer_addf (&query,
                              "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
                              "<epp xmlns='urn:ietf:params:xml:ns:epp-1.0'"
                              " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
                              " xsi:schemaLocation='urn:ietf:params:xml:ns:epp-1.0"
                              " epp-1.0.xsd'>"
                              "<command>"
                              "<check>"
                              "<obj:check xmlns:obj='%s'>",
                              ARRAY_GET (&state->object_types, type)))
    {
      return -1;
    }

  for (i = 0; i < count; ++i)
    {
      if (-1 == VINK_buffer_addf (&query, "<obj:name>%s</obj:name>", objects[i]))
        {
          ARRAY_FREE (&query);

          return -1;
        }
    }

  if (-1 == VINK_buffer_addf (&query,
                              "</check>"
                              "<clTRID>%s</clTRID>"
                              "</command>"
                              "</epp>", trid))
    {
      ARRAY_FREE (&query);

      return -1;
    }

  result = epp_queue_stanza (vink_client_state (client),
                             &ARRAY_GET (&query, 0));

  ARRAY_FREE (&query);

  return result;
}
