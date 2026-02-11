isNumeric(bool integerOnly) const {
  if(!_isPrimitive) {
    return false;
  }

  if(integerOnly) {
    switch(_primitiveType) {
      case TIPO_CARACTERE:
      case TIPO_INTEIRO:
      case TIPO_LOGICO:
      case TIPO_ALL:
        return true;
      case TIPO_REAL:
      case TIPO_LITERAL:
      case TIPO_NULO:
      default:
        return false;
    }
  } else {
    switch(_primitiveType) {
      case TIPO_CARACTERE:
      case TIPO_INTEIRO:
      case TIPO_LOGICO:
      case TIPO_REAL:
      case TIPO_ALL:
        return true;
      case TIPO_LITERAL:
      case TIPO_NULO:
      default:
        return false;
    }
  }
}
