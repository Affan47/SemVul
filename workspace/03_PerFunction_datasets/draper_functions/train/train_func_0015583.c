vector_fmul_window_sse(float *dst, const float *src0, const float *src1,
                                   const float *win, float add_bias, int len){
#if HAVE_6REGS
    if(add_bias == 0){
        x86_reg i = -len*4;
        x86_reg j = len*4-16;
        __asm__ volatile(
            "1: \n"
            "movaps       (%5,%1), %%xmm1 \n"
            "movaps       (%5,%0), %%xmm0 \n"
            "movaps       (%4,%1), %%xmm5 \n"
            "movaps       (%3,%0), %%xmm4 \n"
            "shufps $0x1b, %%xmm1, %%xmm1 \n"
            "shufps $0x1b, %%xmm5, %%xmm5 \n"
            "movaps        %%xmm0, %%xmm2 \n"
            "movaps        %%xmm1, %%xmm3 \n"
            "mulps         %%xmm4, %%xmm2 \n"
            "mulps         %%xmm5, %%xmm3 \n"
            "mulps         %%xmm4, %%xmm1 \n"
            "mulps         %%xmm5, %%xmm0 \n"
            "addps         %%xmm3, %%xmm2 \n"
            "subps         %%xmm0, %%xmm1 \n"
            "shufps $0x1b, %%xmm2, %%xmm2 \n"
            "movaps        %%xmm1, (%2,%0) \n"
            "movaps        %%xmm2, (%2,%1) \n"
            "sub $16, %1 \n"
            "add $16, %0 \n"
            "jl 1b \n"
            :"+r"(i), "+r"(j)
            :"r"(dst+len), "r"(src0+len), "r"(src1), "r"(win+len)
        );
    }else
#endif
        ff_vector_fmul_window_c(dst, src0, src1, win, add_bias, len);
}
