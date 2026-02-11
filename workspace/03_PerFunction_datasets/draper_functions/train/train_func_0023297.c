__indirect_glProgramNamedParameter4dNV(GLuint id, GLsizei len, const GLubyte * name, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    struct glx_context * const gc = __glXGetCurrentContext();
    const GLuint cmdlen = 44 + __GLX_PAD(len);
    if (len < 0) {
        __glXSetError(gc, GL_INVALID_VALUE);
        return;
    }
    if (__builtin_expect(len >= 0, 1)) {
emit_header(gc->pc, X_GLrop_ProgramNamedParameter4dvNV, cmdlen);
(void) memcpy((void *)(gc->pc + 4), (void *)(&x), 8);
(void) memcpy((void *)(gc->pc + 12), (void *)(&y), 8);
(void) memcpy((void *)(gc->pc + 20), (void *)(&z), 8);
(void) memcpy((void *)(gc->pc + 28), (void *)(&w), 8);
(void) memcpy((void *)(gc->pc + 36), (void *)(&id), 4);
(void) memcpy((void *)(gc->pc + 40), (void *)(&len), 4);
(void) memcpy((void *)(gc->pc + 44), (void *)(name), len);
gc->pc += cmdlen;
if (__builtin_expect(gc->pc > gc->limit, 0)) { (void) __glXFlushRenderBuffer(gc, gc->pc); }
    }
}
