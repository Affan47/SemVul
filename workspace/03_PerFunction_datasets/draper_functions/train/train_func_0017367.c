getDisplayText( QString& text )
{

  switch (_base) {
  case 16:
    Translate::ByteToHex(text,_data);
    break;
  case 8:
    Translate::ByteToOctal(text,_data);
    break;
  case 2:
    Translate::ByteToBinary(text,_data);
    break;
  case -1:
    Translate::ByteToChar(text,_data);
    break;
  default:

    return false;
  }
  return true;
}
