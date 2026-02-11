fribidi_unicode_to_cp1255_c (

  FriBidiChar uch
)
{
  if (uch >= UNI_ALEF && uch <= UNI_TAV)
    return (char) (uch - UNI_ALEF + ISO_ALEF);
  if (uch >= UNI_SHEVA && uch <= UNI_SOF_PASUQ)
    return (char) (uch - UNI_SHEVA + CP1255_SHEVA);
  if (uch >= UNI_DOUBLE_VAV && uch <= UNI_GERSHAYIM)
    return (char) (uch - UNI_DOUBLE_VAV + CP1255_DOUBLE_VAV);

  if (uch == UNI_LRM || uch==UNI_RLM)
    return (char) (uch - UNI_LRM + CP1255_LRM);

  else if (uch < 256)
    return (char) uch;
  else
    return '?';
}
