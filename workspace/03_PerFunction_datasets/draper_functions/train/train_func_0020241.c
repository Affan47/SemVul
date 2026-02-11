universal_by_number(const enum universals_n kind,
				     const int value)
{
  struct universal source;

  source.kind = kind;

  switch (source.kind) {
  case VUT_NONE:

    source.value.advance = NULL;

    return source;
  case VUT_ADVANCE:
    source.value.advance = advance_by_number(value);
    if (source.value.advance != NULL) {
      return source;
    }
    break;
  case VUT_GOVERNMENT:
    source.value.govern = government_by_number(value);
    if (source.value.govern != NULL) {
      return source;
    }
    break;
  case VUT_IMPROVEMENT:
    source.value.building = improvement_by_number(value);
    if (source.value.building != NULL) {
      return source;
    }
    break;
  case VUT_SPECIAL:
    source.value.special = value;
    return source;
  case VUT_TERRAIN:
    source.value.terrain = terrain_by_number(value);
    if (source.value.terrain != NULL) {
      return source;
    }
    break;
  case VUT_NATION:
    source.value.nation = nation_by_number(value);
    if (source.value.nation != NULL) {
      return source;
    }
    break;
  case VUT_UTYPE:
    source.value.utype = utype_by_number(value);
    if (source.value.utype != NULL) {
      return source;
    }
    break;
  case VUT_UTFLAG:
    source.value.unitflag = value;
    return source;
  case VUT_UCLASS:
    source.value.uclass = uclass_by_number(value);
    if (source.value.uclass != NULL) {
      return source;
    }
    break;
  case VUT_UCFLAG:
    source.value.unitclassflag = value;
    return source;
  case VUT_OTYPE:
    source.value.outputtype = value;
    return source;
  case VUT_SPECIALIST:
    source.value.specialist = specialist_by_number(value);
    return source;
  case VUT_MINSIZE:
    source.value.minsize = value;
    return source;
  case VUT_AI_LEVEL:
    source.value.ai_level = value;
    return source;
  case VUT_TERRAINCLASS:
    source.value.terrainclass = value;
    return source;
  case VUT_BASE:
    source.value.base = base_by_number(value);
    return source;
  case VUT_MINYEAR:
    source.value.minyear = value;
    return source;
  case VUT_TERRAINALTER:
    source.value.terrainalter = value;
    return source;
  case VUT_CITYTILE:
    source.value.citytile = value;
    return source;
  case VUT_COUNT:
    break;
  }


  source.kind = universals_n_invalid();

  source.value.advance = NULL;

  return source;
}
