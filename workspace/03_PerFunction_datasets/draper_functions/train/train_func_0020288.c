build_decrypt_dictionaries(struct ASPK *stream) {
  unsigned int counter;
  uint32_t ret;
  int oob;

  if (!getbits(stream, 1, &oob)) memset(stream->decrypt_dict, 0, 0x2f5);
  if (oob) return 0;

  for (counter = 0; counter < 19; counter++) {
    stream->array1[counter]=getbits(stream, 4, &oob);
    if (oob) return 0;
  }

  if (!build_decrypt_array(stream, stream->array1, 3)) return 0;

  counter = 0;
  while (counter < 757) {
    ret = getdec(stream, 3, &oob);
    if (oob) return 0;
    if (ret >= 16) {
      if (ret != 16) {
	if (ret == 17) ret = 3 + getbits(stream, 3, &oob);
	else ret = 11 + getbits(stream, 7, &oob);
	if (oob) return 0;
	while (ret) {
	  if (counter >= 757) break;
	  stream->array2[1+counter] = 0;
	  counter++;
	  ret--;
	}
      } else {
	ret = 3 + getbits(stream, 2, &oob);
	if (oob) return 0;
	while (ret) {
	  if (counter >= 757) break;
	  stream->array2[1+counter] = stream->array2[counter];
	  counter++;
	  ret--;
	}
      }
    } else {
      stream->array2[1+counter] = (stream->decrypt_dict[counter] + ret) & 0xF;
      counter++;
    }
  }

  if (!build_decrypt_array(stream, &stream->array2[1], 0)  || !build_decrypt_array(stream, &stream->array2[722], 1)  || !build_decrypt_array(stream, &stream->array2[750], 2)  ) return 0;

  stream->dict_ok = 0;
  for (counter = 0; counter < 8; counter++) {
    if (stream->array2[750+counter] != 3) {
      stream->dict_ok = 1;
      break;
    }
  }

  memcpy(stream->decrypt_dict,&stream->array2[1],757);

  return 1;
}
