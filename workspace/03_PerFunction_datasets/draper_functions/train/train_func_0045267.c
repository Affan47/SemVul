untag_arbitrary(Pulse_Tag *tag, Eina_Binbuf **val)
{
   uint8_t *ret;
   uint32_t len;

   if (!untag_uint32(tag, &len)) return 0;
   ret = tag->data + tag->size;
   if (*ret != PA_TAG_ARBITRARY) return 0;
   ret += PA_TAG_SIZE_ARBITRARY;

   *val = eina_binbuf_new();
   eina_binbuf_append_length(*val, ret, len);
   ret += len;
   tag->size = ret - tag->data;
   return ret;
}
