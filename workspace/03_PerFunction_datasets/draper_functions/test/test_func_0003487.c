fbconfigs_compatible(const struct glx_config * const a,
                     const struct glx_config * const b)
{
   MATCH_DONT_CARE(doubleBufferMode);
   MATCH_DONT_CARE(visualType);
   MATCH_DONT_CARE(visualRating);
   MATCH_DONT_CARE(xRenderable);
   MATCH_DONT_CARE(fbconfigID);
   MATCH_DONT_CARE(swapMethod);

   MATCH_MINIMUM(rgbBits);
   MATCH_MINIMUM(numAuxBuffers);
   MATCH_MINIMUM(redBits);
   MATCH_MINIMUM(greenBits);
   MATCH_MINIMUM(blueBits);
   MATCH_MINIMUM(alphaBits);
   MATCH_MINIMUM(depthBits);
   MATCH_MINIMUM(stencilBits);
   MATCH_MINIMUM(accumRedBits);
   MATCH_MINIMUM(accumGreenBits);
   MATCH_MINIMUM(accumBlueBits);
   MATCH_MINIMUM(accumAlphaBits);
   MATCH_MINIMUM(sampleBuffers);
   MATCH_MINIMUM(maxPbufferWidth);
   MATCH_MINIMUM(maxPbufferHeight);
   MATCH_MINIMUM(maxPbufferPixels);
   MATCH_MINIMUM(samples);

   MATCH_DONT_CARE(stereoMode);
   MATCH_EXACT(level);

   MATCH_MASK(drawableType);
   MATCH_MASK(renderType);


   if (a->transparentPixel != (int) GLX_DONT_CARE && a->transparentPixel != 0) {
      if (a->transparentPixel == GLX_NONE) {
         if (b->transparentPixel != GLX_NONE && b->transparentPixel != 0)
            return False;
      }
      else {
         MATCH_EXACT(transparentPixel);
      }

      switch (a->transparentPixel) {
      case GLX_TRANSPARENT_RGB:
         MATCH_DONT_CARE(transparentRed);
         MATCH_DONT_CARE(transparentGreen);
         MATCH_DONT_CARE(transparentBlue);
         MATCH_DONT_CARE(transparentAlpha);
         break;

      case GLX_TRANSPARENT_INDEX:
         MATCH_DONT_CARE(transparentIndex);
         break;

      default:
         break;
      }
   }

   return True;
}
