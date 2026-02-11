ftio_rec_swapfunc(struct ftio *ftio)
{

  u_int8 s_ver, d_ver, agg_ver, agg_method;
  void *ret;

  s_ver = ftio->fth.s_version;
  d_ver = ftio->fth.d_version;

  agg_ver = ftio->fth.agg_version;
  agg_method = ftio->fth.agg_method;

  switch (s_ver) {

    case 1:
      ret = fts1rec_swap_compat;
      break;

    case 3:
      switch (ftio->fth.d_version) {

        case 1:
          ret = fts3rec_swap_v1;
          break;

        case 5:
          ret = fts3rec_swap_v5;
          break;

        case 6:
          ret = fts3rec_swap_v6;
          break;

        case 7:
          ret = fts3rec_swap_v7;
          break;

        case 8:
          if (agg_ver != 2) {
            fterr_warnx("Unsupported agg_version %d", (int)agg_ver);
            ret = (void*)0L;
            break;
          }

          switch (agg_method) {

            case 1:
              ret = fts3rec_swap_v8_1;
              break;

            case 2:
              ret = fts3rec_swap_v8_2;
              break;

            case 3:
              ret = fts3rec_swap_v8_3;
              break;

            case 4:
              ret = fts3rec_swap_v8_4;
              break;

            case 5:
              ret = fts3rec_swap_v8_5;
              break;

            case 6:
              ret = fts3rec_swap_v8_6;
              break;

            case 7:
              ret = fts3rec_swap_v8_7;
              break;

            case 8:
              ret = fts3rec_swap_v8_8;
              break;

            case 9:
              ret = fts3rec_swap_v8_9;
              break;

            case 10:
              ret = fts3rec_swap_v8_10;
              break;

            case 11:
              ret = fts3rec_swap_v8_11;
              break;

            case 12:
              ret = fts3rec_swap_v8_12;
              break;

            case 13:
              ret = fts3rec_swap_v8_13;
              break;

            case 14:
              ret = fts3rec_swap_v8_14;
              break;

            default:
              fterr_warnx("Unsupported agg_method %d", (int)agg_method);
              ret = (void*)0L;
              break;

          }
          break;

        case 1005:
          ret = fts3rec_swap_v1005;
          break;

        default:
          fterr_warnx("Unsupported d_version %d", (int)ftio->fth.d_version);
          ret = (void*)0L;
          break;

      }
      break;

    default:
      fterr_warnx("Unsupported s_version %d", (int)s_ver);
      ret = (void*)0L;
      break;

  }

  return ret;

}
