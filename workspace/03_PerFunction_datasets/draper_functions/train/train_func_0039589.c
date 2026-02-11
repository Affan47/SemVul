pixel_point(struct gl_context *ctx, const SWvertex *vert)
{
   SWcontext *swrast = SWRAST_CONTEXT(ctx);


   SWspan *span = &(swrast->PointSpan);
   GLuint count;

   CULL_INVALID(vert);


   span->interpMask = 0;
   span->arrayMask = SPAN_XY | SPAN_Z;
   span->arrayMask |= SPAN_RGBA;

   span->arrayAttribs = swrast->_ActiveAttribMask;


   span->attrStart[VARYING_SLOT_POS][3] = 1.0F;
   span->attrStepX[VARYING_SLOT_POS][3] = 0.0F;
   span->attrStepY[VARYING_SLOT_POS][3] = 0.0F;


   if (span->end >= SWRAST_MAX_WIDTH ||
       (swrast->_RasterMask & (BLEND_BIT | LOGIC_OP_BIT | MASKING_BIT)) ||
       span->facing != swrast->PointLineFacing) {
      if (span->end > 0) {
	 _swrast_write_rgba_span(ctx, span);
         span->end = 0;
      }
   }

   count = span->end;

   span->facing = swrast->PointLineFacing;


   span->array->rgba[count][RCOMP] = vert->color[0];
   span->array->rgba[count][GCOMP] = vert->color[1];
   span->array->rgba[count][BCOMP] = vert->color[2];
   span->array->rgba[count][ACOMP] = vert->color[3];

   ATTRIB_LOOP_BEGIN
      COPY_4V(span->array->attribs[attr][count], vert->attrib[attr]);
   ATTRIB_LOOP_END


   span->array->x[count] = (GLint) vert->attrib[VARYING_SLOT_POS][0];
   span->array->y[count] = (GLint) vert->attrib[VARYING_SLOT_POS][1];
   span->array->z[count] = (GLint) (vert->attrib[VARYING_SLOT_POS][2] + 0.5F);

   span->end = count + 1;
   ASSERT(span->end <= SWRAST_MAX_WIDTH);
}
