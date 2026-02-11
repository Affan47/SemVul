GetPropertyByIndex (int aIndex,
                                      NPVariant *_result)
{
  TOTEM_LOG_SETTER (aIndex, totemGMPControls);

  switch (Properties (aIndex)) {
    case eCurrentPosition:

      return DoubleVariant (_result, double (Plugin()->GetTime()) / 1000.0);

    case eCurrentItem:

    case eCurrentPositionTimecode:

    case eCurrentPositionString:

      TOTEM_WARN_GETTER_UNIMPLEMENTED (aIndex, totemGMPControls);
      return StringVariant (_result, "");

    case eAudioLanguageCount:

    case eCurrentAudioLanguage:

    case eCurrentAudioLanguageIndex:

    case eCurrentMarker:

      TOTEM_WARN_GETTER_UNIMPLEMENTED (aIndex, totemGMPControls);
      return Int32Variant (_result, 0);
  }

  return false;
}
