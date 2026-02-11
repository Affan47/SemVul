resample_linear_row_float(GLint srcWidth, GLint dstWidth,
                          const GLvoid *srcBuffer0, const GLvoid *srcBuffer1,
                          GLvoid *dstBuffer, GLboolean flip, GLfloat rowWeight)
{
   const GLfloat (*srcColor0)[4] = (const GLfloat (*)[4]) srcBuffer0;
   const GLfloat (*srcColor1)[4] = (const GLfloat (*)[4]) srcBuffer1;
   GLfloat (*dstColor)[4] = (GLfloat (*)[4]) dstBuffer;
   GLint dstCol;

   for (dstCol = 0; dstCol < dstWidth; dstCol++) {
      const GLfloat srcCol = (dstCol + 0.5F) / dstWidth * srcWidth - 0.5F;
      GLint srcCol0 = MAX2(0, IFLOOR(srcCol));
      GLint srcCol1 = srcCol0 + 1;
      GLfloat colWeight = srcCol - srcCol0;
      GLfloat red, green, blue, alpha;

      ASSERT(srcCol0 < srcWidth);
      ASSERT(srcCol1 <= srcWidth);

      if (srcCol1 == srcWidth) {

         srcCol1--;
         colWeight = 0.0;
      }

      if (flip) {
         srcCol0 = srcWidth - 1 - srcCol0;
         srcCol1 = srcWidth - 1 - srcCol1;
      }

      red = lerp_2d(colWeight, rowWeight,
                    srcColor0[srcCol0][RCOMP], srcColor0[srcCol1][RCOMP],
                    srcColor1[srcCol0][RCOMP], srcColor1[srcCol1][RCOMP]);
      green = lerp_2d(colWeight, rowWeight,
                    srcColor0[srcCol0][GCOMP], srcColor0[srcCol1][GCOMP],
                    srcColor1[srcCol0][GCOMP], srcColor1[srcCol1][GCOMP]);
      blue = lerp_2d(colWeight, rowWeight,
                    srcColor0[srcCol0][BCOMP], srcColor0[srcCol1][BCOMP],
                    srcColor1[srcCol0][BCOMP], srcColor1[srcCol1][BCOMP]);
      alpha = lerp_2d(colWeight, rowWeight,
                    srcColor0[srcCol0][ACOMP], srcColor0[srcCol1][ACOMP],
                    srcColor1[srcCol0][ACOMP], srcColor1[srcCol1][ACOMP]);

      dstColor[dstCol][RCOMP] = red;
      dstColor[dstCol][GCOMP] = green;
      dstColor[dstCol][BCOMP] = blue;
      dstColor[dstCol][ACOMP] = alpha;
   }
}
