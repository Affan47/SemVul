weighting_filter(const int16_t *e,
                             int16_t x[40])
{
#if defined(__GNUC__)  &&  defined(__i386__)


    static const union
    {
        int16_t gsm_H[12];
        uint64_t x[3];
    } gsm_H =
    {
        {
            -134, -374, 0, 2054, 5741, 8192, 5741, 2054, 0, -374, -134, 0
        }

    };

    __asm__ __volatile__(
        " emms;\n"
        " addl $-10,%%ecx;\n"
        " movl $0x1000,%%eax;\n"
        " movd %%eax,%%mm5;\n"
        " movq %[gsm_H],%%mm1;\n"
        " movq %[gsm_H8],%%mm2;\n"
        " movq %[gsm_H16],%%mm3;\n"
        " xorl %%esi,%%esi;\n"
        " .p2align 2;\n"
        "1:;\n"
        " movq (%%ecx,%%esi,2),%%mm0;\n"
        " pmaddwd %%mm1,%%mm0;\n"

        " movq 8(%%ecx,%%esi,2),%%mm4;\n"
        " pmaddwd %%mm2,%%mm4;\n"
        " paddd %%mm4,%%mm0;\n"

        " movq 16(%%ecx,%%esi,2),%%mm4;\n"
        " pmaddwd %%mm3,%%mm4;\n"
        " paddd %%mm4,%%mm0;\n"

        " movq %%mm0,%%mm4;\n"
        " punpckhdq %%mm0,%%mm4;\n"
        " paddd %%mm4,%%mm0;\n"

        " paddd %%mm5,%%mm0;\n"
        " psrad $13,%%mm0;\n"
        " packssdw %%mm0,%%mm0;\n"
        " movd %%mm0,%%eax;\n"
        " movw %%ax,(%%edi,%%esi,2);\n"
        " incl %%esi;\n"
        " cmpl $39,%%esi;\n"
        " jle 1b;\n"
        " emms;\n"
        :
        : "c" (e), "D" (x), [gsm_H] "X" (gsm_H.x[0]), [gsm_H8] "X" (gsm_H.x[1]), [gsm_H16] "X" (gsm_H.x[2])
        : "eax", "edx", "esi"
    );
#else
    int32_t L_result;
    int k;


    e -= 5;


    for (k = 0;  k < 40;  k++)
    {
        L_result = 8192 >> 1;


#undef STEP
#define STEP(i,H) (e[k + i] * (int32_t) H)


        L_result += STEP( 0,  -134);
        L_result += STEP( 1,  -374);

        L_result += STEP( 3,  2054);
        L_result += STEP( 4,  5741);
        L_result += STEP( 5,  8192);
        L_result += STEP( 6,  5741);
        L_result += STEP( 7,  2054);

        L_result += STEP( 9,  -374);
        L_result += STEP(10,  -134);


        L_result >>= 13;
        x[k] = saturate(L_result);
    }

#endif
}
