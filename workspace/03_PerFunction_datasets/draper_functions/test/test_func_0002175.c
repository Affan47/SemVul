i915ColorMask(struct gl_context * ctx,
              GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
   struct i915_context *i915 = I915_CONTEXT(ctx);
   GLuint tmp = i915->state.Ctx[I915_CTXREG_LIS5] & ~S5_WRITEDISABLE_MASK;

   DBG("%s r(%d) g(%d) b(%d) a(%d)\n", __FUNCTION__, r, g, b,
       a);

   if (!r)
      tmp |= S5_WRITEDISABLE_RED;
   if (!g)
      tmp |= S5_WRITEDISABLE_GREEN;
   if (!b)
      tmp |= S5_WRITEDISABLE_BLUE;
   if (!a)
      tmp |= S5_WRITEDISABLE_ALPHA;

   if (tmp != i915->state.Ctx[I915_CTXREG_LIS5]) {
      I915_STATECHANGE(i915, I915_UPLOAD_CTX);
      i915->state.Ctx[I915_CTXREG_LIS5] = tmp;
   }
}
