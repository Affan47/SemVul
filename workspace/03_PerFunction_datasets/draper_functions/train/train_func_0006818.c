glDeleteTexturesEXT(GLsizei n, const GLuint * textures)
{
    struct glx_context * const gc = __glXGetCurrentContext();

#if defined(GLX_DIRECT_RENDERING) && !defined(GLX_USE_APPLEGL)
    if (gc->isDirect) {
        const _glapi_proc *const disp_table = (_glapi_proc *)GET_DISPATCH();
        PFNGLDELETETEXTURESEXTPROC p =
            (PFNGLDELETETEXTURESEXTPROC) disp_table[327];
    p(n, textures);
    } else
#endif
    {
    struct glx_context * const gc = __glXGetCurrentContext();
    Display * const dpy = gc->currentDpy;
    const GLuint cmdlen = 4 + __GLX_PAD((n * 4));
    if (n < 0) {
        __glXSetError(gc, GL_INVALID_VALUE);
        return;
    }
    if (__builtin_expect((n >= 0) && (dpy != NULL), 1)) {
        GLubyte const * pc = __glXSetupVendorRequest(gc, X_GLXVendorPrivate, X_GLvop_DeleteTexturesEXT, cmdlen);
(void) memcpy((void *)(pc + 0), (void *)(&n), 4);
(void) memcpy((void *)(pc + 4), (void *)(textures), (n * 4));
        UnlockDisplay(dpy); SyncHandle();
    }
    return;
}
}
