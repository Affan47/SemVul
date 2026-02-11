source_report_start(Generic_t *self, datum_t *key, client_t *client, void *arg)
{
   int rc;
   char *name = (char*) key->data;
   Source_t *source = (Source_t*) self;

   if (self->id == CLUSTER_NODE)
      {
            rc=xml_print(client, "<CLUSTER NAME=\"%s\" LOCALTIME=\"%u\" OWNER=\"%s\" "
               "LATLONG=\"%s\" URL=\"%s\">\n",
               name, source->localtime, getfield(source->strings, source->owner),
               getfield(source->strings, source->latlong),
               getfield(source->strings, source->url));
      }
   else
      {
            rc=xml_print(client, "<GRID NAME=\"%s\" AUTHORITY=\"%s\" "
               "LOCALTIME=\"%u\">\n",
               name, getfield(source->strings, source->authority_ptr), source->localtime);
      }

   return rc;
}
