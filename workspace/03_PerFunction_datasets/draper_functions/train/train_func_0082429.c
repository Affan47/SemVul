get_free_text_quadding (PopplerAnnotFreeText *poppler_annot)
{
    switch (poppler_annot_free_text_get_quadding (poppler_annot))
    {
      case POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED:
        return "Left Justified";
      case POPPLER_ANNOT_FREE_TEXT_QUADDING_CENTERED:
        return "Centered";
      case POPPLER_ANNOT_FREE_TEXT_QUADDING_RIGHT_JUSTIFIED:
        return "Right Justified";
      default:
        break;
    }

  return "Unknown";
}
