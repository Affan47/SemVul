StringToPreviewType(const char *option)
{
  PreviewType
    preview_type = UndefinedPreview;

  if (LocaleCompare("Rotate",option) == 0)
    preview_type=RotatePreview;
  else if (LocaleCompare("Shear",option) == 0)
    preview_type=ShearPreview;
  else if (LocaleCompare("Roll",option) == 0)
    preview_type=RollPreview;
  else if (LocaleCompare("Hue",option) == 0)
    preview_type=HuePreview;
  else if (LocaleCompare("Saturation",option) == 0)
    preview_type=SaturationPreview;
  else if (LocaleCompare("Brightness",option) == 0)
    preview_type=BrightnessPreview;
  else if (LocaleCompare("Gamma",option) == 0)
    preview_type=GammaPreview;
  else if (LocaleCompare("Spiff",option) == 0)
    preview_type=SpiffPreview;
  else if (LocaleCompare("Dull",option) == 0)
    preview_type=DullPreview;
  else if (LocaleCompare("Grayscale",option) == 0)
    preview_type=GrayscalePreview;
  else if (LocaleCompare("Quantize",option) == 0)
    preview_type=QuantizePreview;
  else if (LocaleCompare("Despeckle",option) == 0)
    preview_type=DespecklePreview;
  else if (LocaleCompare("ReduceNoise",option) == 0)
    preview_type=ReduceNoisePreview;
  else if (LocaleCompare("AddNoise",option) == 0)
    preview_type=AddNoisePreview;
  else if (LocaleCompare("Sharpen",option) == 0)
    preview_type=SharpenPreview;
  else if (LocaleCompare("Blur",option) == 0)
    preview_type=BlurPreview;
  else if (LocaleCompare("Threshold",option) == 0)
    preview_type=ThresholdPreview;
  else if (LocaleCompare("EdgeDetect",option) == 0)
    preview_type=EdgeDetectPreview;
  else if (LocaleCompare("Spread",option) == 0)
    preview_type=SpreadPreview;
  else if (LocaleCompare("Shade",option) == 0)
    preview_type=ShadePreview;
  else if (LocaleCompare("Raise",option) == 0)
    preview_type=RaisePreview;
  else if (LocaleCompare("Segment",option) == 0)
    preview_type=SegmentPreview;
  else if (LocaleCompare("Solarize",option) == 0)
    preview_type=SolarizePreview;
  else if (LocaleCompare("Swirl",option) == 0)
    preview_type=SwirlPreview;
  else if (LocaleCompare("Implode",option) == 0)
    preview_type=ImplodePreview;
  else if (LocaleCompare("Wave",option) == 0)
    preview_type=WavePreview;
  else if (LocaleCompare("OilPaint",option) == 0)
    preview_type=OilPaintPreview;
  else if (LocaleCompare("CharcoalDrawing",option) == 0)
    preview_type=CharcoalDrawingPreview;
  else if (LocaleCompare("JPEG",option) == 0)
    preview_type=JPEGPreview;

  return preview_type;
}
