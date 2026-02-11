HPDF_CMapEncoder_AddJWWLineHead  (HPDF_Encoder        encoder,
                                  const HPDF_UINT16  *code)
{
    HPDF_CMapEncoderAttr attr = (HPDF_CMapEncoderAttr)encoder->attr;
    HPDF_UINT i, j;

    HPDF_PTRACE ((" HPDF_CMapEncoder_AddJWWLineHead\n"));

    for (i = 0; i < HPDF_MAX_JWW_NUM; i++) {
        if (*code == 0)
            break;

        for (j = 0; j < HPDF_MAX_JWW_NUM; j++) {
            if (attr->jww_line_head[j] == *code)
                break;

            if (attr->jww_line_head[j] == 0) {
                attr->jww_line_head[j] = *code;
                break;
            }

            if (j == HPDF_MAX_JWW_NUM - 1)
                return HPDF_SetError (encoder->error,
                                HPDF_EXCEED_JWW_CODE_NUM_LIMIT, i);
        }

        code++;
    }

    return HPDF_OK;
}
