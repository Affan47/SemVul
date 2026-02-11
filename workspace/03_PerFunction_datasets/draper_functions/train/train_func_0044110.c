cast5_encrypt(struct cast5_state *cast5, char *in, char *out)
{
  U32 tmp, left, right;
  left  = CHAR_TO_WORD(in);
  right = CHAR_TO_WORD(in+4);

  CAST5_STEP1(cast5->mask_key[0],  cast5->rot_key[0],  tmp, left, right);
  CAST5_STEP2(cast5->mask_key[1],  cast5->rot_key[1],  tmp, right, left);
  CAST5_STEP3(cast5->mask_key[2],  cast5->rot_key[2],  tmp, left, right);
  CAST5_STEP1(cast5->mask_key[3],  cast5->rot_key[3],  tmp, right, left);
  CAST5_STEP2(cast5->mask_key[4],  cast5->rot_key[4],  tmp, left, right);
  CAST5_STEP3(cast5->mask_key[5],  cast5->rot_key[5],  tmp, right, left);
  CAST5_STEP1(cast5->mask_key[6],  cast5->rot_key[6],  tmp, left, right);
  CAST5_STEP2(cast5->mask_key[7],  cast5->rot_key[7],  tmp, right, left);
  CAST5_STEP3(cast5->mask_key[8],  cast5->rot_key[8],  tmp, left, right);
  CAST5_STEP1(cast5->mask_key[9],  cast5->rot_key[9],  tmp, right, left);
  CAST5_STEP2(cast5->mask_key[10], cast5->rot_key[10], tmp, left, right);
  CAST5_STEP3(cast5->mask_key[11], cast5->rot_key[11], tmp, right, left);
  if (cast5->rounds == 16) {
    CAST5_STEP1(cast5->mask_key[12], cast5->rot_key[12], tmp, left, right);
    CAST5_STEP2(cast5->mask_key[13], cast5->rot_key[13], tmp, right, left);
    CAST5_STEP3(cast5->mask_key[14], cast5->rot_key[14], tmp, left, right);
    CAST5_STEP1(cast5->mask_key[15], cast5->rot_key[15], tmp, right, left);
  }

  WORD_TO_CHAR(right, out);
  WORD_TO_CHAR(left,  out+4);
}
