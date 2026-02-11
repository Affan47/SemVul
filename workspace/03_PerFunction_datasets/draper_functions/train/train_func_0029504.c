eet_data_get_f32p32(const Eet_Dictionary *ed,
                    const void           *src,
                    const void           *src_end,
                    void                 *dst)
{
   Eina_F32p32 *fp;
   int idx;

   fp = (Eina_F32p32 *)dst;

   if (!ed)
     {
        const char *s, *p;
        int len;

        s = (const char *)src;
        p = s;
        len = 0;
        while ((p < (const char *)src_end) && (*p != 0)) { len++; p++; }

        if (!(eina_convert_atofp(s, len, fp)))
          return -1;

        return 1;
     }

   if (eet_data_get_int(ed, src, src_end, &idx) < 0)
     return -1;

   if (!eet_dictionary_string_get_fp(ed, idx, fp))
     return -1;

   return 1;
}
