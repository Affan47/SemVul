BIGINT_test(BI_CTX *ctx)
{
    int res = 1;

#ifndef CONFIG_INTEGER_8BIT
#ifndef CONFIG_INTEGER_16BIT
    bigint *bi_data, *bi_exp, *bi_res;
    const char *expnt, *plaintext, *mod;
    uint8_t compare[MAX_KEY_BYTE_SIZE];


    plaintext =
        "01aaaaaaaaaabbbbbbbbbbbbbbbccccccccccccccdddddddddddddeeeeeeeeee";

    mod = "C30773C8ABE09FCC279EE0E5343370DE"
          "8B2FFDB6059271E3005A7CEEF0D35E0A"
          "1F9915D95E63560836CC2EB2C289270D"
          "BCAE8CAF6F5E907FC2759EE220071E1B";

    expnt = "A1E556CD1738E10DF539E35101334E97"
          "BE8D391C57A5C89A7AD9A2EA2ACA1B3D"
          "F3140F5091CC535CBAA47CEC4159EE1F"
          "B6A3661AFF1AB758426EAB158452A9B9";

    bi_data = bi_import(ctx, (uint8_t *)plaintext, strlen(plaintext));
    bi_exp = int_to_bi(ctx, 0x10001);
    bi_set_mod(ctx, bi_str_import(ctx, mod), 0);
    bi_res = bi_mod_power(ctx, bi_data, bi_exp);

    bi_data = bi_res;

    bi_exp = bi_str_import(ctx, expnt);
    bi_res = bi_mod_power(ctx, bi_data, bi_exp);
    bi_free_mod(ctx, 0);

    bi_export(ctx, bi_res, compare, 64);
    if (memcmp(plaintext, compare, 64) != 0)
        goto end;
#endif
#endif


    {
        bigint *bi_x = bi_str_import(ctx,
                "AFD5060E224B70DA99EFB385BA5C0D2BEA0AD1DAAA52686E1A02D677BC65C1DA7A496BBDCC02999E8814F10AFC4B8E0DD4E6687E0762CE717A5EA1E452B5C56065C8431F0FB9D23CFF3A4B4149798C0670AF7F9565A0EAE5CF1AB16A1F0C3DD5E485DC5ABB96EBE0B6778A15B7302CBCE358E4BF2E2E30932758AC6EFA9F5828");
        bigint *arg2 = bi_clone(ctx, bi_x);
        bigint *arg3 = bi_clone(ctx, bi_x);
        bigint *sqr_result = bi_square(ctx, bi_x);
        bigint *mlt_result = bi_multiply(ctx, arg2, arg3);

        if (bi_compare(sqr_result, mlt_result) != 0)
        {
            bi_print("SQR_RESULT", sqr_result);
            bi_print("MLT_RESULT", mlt_result);
            bi_free(ctx, sqr_result);
            bi_free(ctx, mlt_result);
            goto end;
        }

        bi_free(ctx, sqr_result);
        bi_free(ctx, mlt_result);
    }

    printf("All BIGINT tests passed\n");
    res = 0;

end:
    return res;
}
