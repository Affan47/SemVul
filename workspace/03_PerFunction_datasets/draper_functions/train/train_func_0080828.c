test_nbit7(int32 fid)
{
    int32       aid1;
    uint16      ref1;
    int i;
    int32       ret;
    intn        errors = 0;
    model_info  m_info;
    comp_info   c_info;
    uint8      *outbuf, *inbuf;
    uint8       test_val;

    outbuf = (uint8 *) HDmalloc(NBIT_SIZE7 * sizeof(uint8));
    inbuf = (uint8 *) HDmalloc(NBIT_SIZE7 * sizeof(uint8));

    for (i = 0; i < NBIT_SIZE7; i++)
        outbuf[i] = (uint8) (i * 3);

    ref1 = Hnewref(fid);
    CHECK_VOID(ref1, 0, "Hnewref");

    MESSAGE(5, printf("Create a new element as a unsigned 8-bit n-bit element with filled ones\n");
        );
    c_info.nbit.nt = DFNT_UINT8;
    c_info.nbit.sign_ext = FALSE;
    c_info.nbit.fill_one = TRUE;
    c_info.nbit.start_bit = NBIT_OFF7;
    c_info.nbit.bit_len = NBIT_BITS7;
    aid1 = HCcreate(fid, NBIT_TAG7, ref1, COMP_MODEL_STDIO, &m_info,
                    COMP_CODE_NBIT, &c_info);
    CHECK_VOID(aid1, FAIL, "HCcreate");

    ret = Hwrite(aid1, NBIT_SIZE7, outbuf);
    if (ret != NBIT_SIZE7)
      {
          fprintf(stderr, "ERROR(%d): Hwrite returned the wrong length: %d\n", __LINE__, (int) ret);
          HEprint(stdout, 0);
          errors++;
      }

    ret = Hendaccess(aid1);
    CHECK_VOID(ret, FAIL, "Hendaccess");

    MESSAGE(5, printf("Verifying data\n");
        );
    ret = Hgetelement(fid, NBIT_TAG7, (uint16) ref1, inbuf);
    if (ret != NBIT_SIZE7)
      {
          HEprint(stderr, 0);
          fprintf(stderr, "ERROR: (%d) Hgetelement returned the wrong length: %d\n", __LINE__, (int) ret);
          errors++;
      }

    for (i = 0; i < ret; i++)
      {
          test_val = (uint8) ((outbuf[i] & NBIT_MASK7A) | NBIT_MASK7B);
          if ((uint8) inbuf[i] != (uint8) test_val)
            {
                printf("test_nbit7: Wrong data at %d, out (%d)%d in %d\n", i, outbuf[i], test_val, inbuf[i]);
                errors++;
            }
      }
    HDfree(outbuf);
    HDfree(inbuf);
    num_errs += errors;
}
