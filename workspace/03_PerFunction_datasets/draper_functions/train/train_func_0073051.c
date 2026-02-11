_evas_common_font_double_int_cmp(const int *key1, __UNUSED__ int key1_length,
				 const int *key2, __UNUSED__ int key2_length)
{
   if (key1[0] - key2[0] == 0) return key1[1] - key2[1];
   return key1[0] - key2[0];
}
