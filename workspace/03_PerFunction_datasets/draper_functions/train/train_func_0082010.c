cut_cairo_set_source_result_color (cairo_t *cr,
                                   CutTestResultStatus status)
{
    gdouble red, green, blue;

    switch (status) {
      case CUT_TEST_RESULT_SUCCESS:
        red = 0x8a / (gdouble)0xff;
        green = 0xe2 / (gdouble)0xff;
        blue = 0x34 / (gdouble)0xff;
        break;
      case CUT_TEST_RESULT_NOTIFICATION:
        red = 0x72 / (gdouble)0xff;
        green = 0x9f / (gdouble)0xff;
        blue = 0xcf / (gdouble)0xff;
        break;
      case CUT_TEST_RESULT_OMISSION:
        red = 0x20 / (gdouble)0xff;
        green = 0x4a / (gdouble)0xff;
        blue = 0x87 / (gdouble)0xff;
        break;
      case CUT_TEST_RESULT_PENDING:
        red = 0x5c / (gdouble)0xff;
        green = 0x35 / (gdouble)0xff;
        blue = 0x66 / (gdouble)0xff;
        break;
      case CUT_TEST_RESULT_FAILURE:
        red = 0xef / (gdouble)0xff;
        green = 0x29 / (gdouble)0xff;
        blue = 0x29 / (gdouble)0xff;
        break;
      case CUT_TEST_RESULT_ERROR:
        red = 0xfc / (gdouble)0xff;
        green = 0xe9 / (gdouble)0xff;
        blue = 0x4f / (gdouble)0xff;
        break;
      default:
        return;
    }

    cairo_set_source_rgb(cr, red, green, blue);
}
