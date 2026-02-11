ecore_x_randr_edid_display_type_digital_get(unsigned char *edid,
                                            unsigned long edid_length)
{
   int version = ecore_x_randr_edid_version_get(edid, edid_length);

   if (version < ECORE_X_RANDR_EDID_VERSION_13) return EINA_FALSE;
   return !!(edid[_ECORE_X_RANDR_EDID_OFFSET_TYPE] &
             _ECORE_X_RANDR_EDID_MASK_DIGITAL);
}
