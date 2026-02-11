get_comb_score (GstVideoFrame * top, GstVideoFrame * bottom)
{
  int j;
  int thisline[MAX_WIDTH];
  int score = 0;
  int height;
  int width;
  int k;

  height = GST_VIDEO_FRAME_COMP_HEIGHT (top, 0);
  width = GST_VIDEO_FRAME_COMP_WIDTH (top, 0);

  memset (thisline, 0, sizeof (thisline));

  k = 0;


  for (j = 2; j < height - 2; j++) {
    guint8 *src1 = GET_LINE_IL (top, bottom, 0, j - 1);
    guint8 *src2 = GET_LINE_IL (top, bottom, 0, j);
    guint8 *src3 = GET_LINE_IL (top, bottom, 0, j + 1);
    int i;

    for (i = 0; i < width; i++) {
      if (src2[i] < MIN (src1[i], src3[i]) - 5 ||
          src2[i] > MAX (src1[i], src3[i]) + 5) {
        if (i > 0) {
          thisline[i] += thisline[i - 1];
        }
        thisline[i]++;
        if (thisline[i] > 1000)
          thisline[i] = 1000;
      } else {
        thisline[i] = 0;
      }
      if (thisline[i] > 100) {
        score++;
      }
    }
  }

  GST_DEBUG ("score %d", score);

  return score;
}
