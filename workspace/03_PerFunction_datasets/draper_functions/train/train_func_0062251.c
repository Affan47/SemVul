ftrec_size(struct ftver *ver)
{

  int ret;

  switch (ver->s_version) {

    case 1:
      ret = sizeof (struct fts1rec_compat);
      break;

    case 3:
      switch (ver->d_version) {

        case 1:
          ret = sizeof (struct fts3rec_v1);
          break;

        case 5:
          ret = sizeof (struct fts3rec_v5);
          break;

        case 6:
          ret = sizeof (struct fts3rec_v6);
          break;

        case 7:
          ret = sizeof (struct fts3rec_v7);
          break;

        case 8:
          if (ver->agg_version != 2) {
            fterr_warnx("Unsupported agg_version %d", (int)ver->agg_version);
            ret = -1;
            break;
          }

          switch (ver->agg_method) {

            case 1:
              ret = sizeof (struct fts3rec_v8_1);
              break;

            case 2:
              ret = sizeof (struct fts3rec_v8_2);
              break;

            case 3:
              ret = sizeof (struct fts3rec_v8_3);
              break;

            case 4:
              ret = sizeof (struct fts3rec_v8_4);
              break;

            case 5:
              ret = sizeof (struct fts3rec_v8_5);
              break;

            case 6:
              ret = sizeof (struct fts3rec_v8_6);
              break;

            case 7:
              ret = sizeof (struct fts3rec_v8_7);
              break;

            case 8:
              ret = sizeof (struct fts3rec_v8_8);
              break;

            case 9:
              ret = sizeof (struct fts3rec_v8_9);
              break;

            case 10:
              ret = sizeof (struct fts3rec_v8_10);
              break;

            case 11:
              ret = sizeof (struct fts3rec_v8_11);
              break;

            case 12:
              ret = sizeof (struct fts3rec_v8_12);
              break;

            case 13:
              ret = sizeof (struct fts3rec_v8_13);
              break;

            case 14:
              ret = sizeof (struct fts3rec_v8_14);
              break;

            default:
              fterr_warnx("Unsupported agg_method %d", (int)ver->agg_method);
              ret = -1;
              break;

          }
          break;

        case 1005:
          ret = sizeof (struct fts3rec_v1005);
          break;

        default:
          fterr_warnx("Unsupported d_version %d", (int)ver->d_version);
          ret = -1;
          break;

      }
      break;

    default:
      fterr_warnx("Unsupported s_version %d", (int)ver->s_version);
      ret = -1;
      break;

  }

  return ret;

}
