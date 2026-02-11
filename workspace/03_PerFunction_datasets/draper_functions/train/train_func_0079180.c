fts3rec_pdu_encode(struct ftencode *enc, void *rec)
{

  switch (enc->ver.d_version) {

    case 1:
      return (fts3rec_pdu_v1_encode(enc, (struct fts3rec_v1*)rec));
      break;

    case 5:
      return (fts3rec_pdu_v5_encode(enc, (struct fts3rec_v5*)rec));
      break;

    case 6:
      return (fts3rec_pdu_v6_encode(enc, (struct fts3rec_v6*)rec));
      break;

    case 7:
      return (fts3rec_pdu_v7_encode(enc, (struct fts3rec_v7*)rec));
      break;

    case 8:

      switch (enc->ver.agg_method) {

        case 1:
          return (fts3rec_pdu_v8_1_encode(enc, (struct fts3rec_v8_1*)rec));
          break;

        case 2:
          return (fts3rec_pdu_v8_2_encode(enc, (struct fts3rec_v8_2*)rec));
          break;

        case 3:
          return (fts3rec_pdu_v8_3_encode(enc, (struct fts3rec_v8_3*)rec));
          break;

        case 4:
          return (fts3rec_pdu_v8_4_encode(enc, (struct fts3rec_v8_4*)rec));
          break;

        case 5:
          return (fts3rec_pdu_v8_5_encode(enc, (struct fts3rec_v8_5*)rec));
          break;

        case 6:
          return (fts3rec_pdu_v8_6_encode(enc, (struct fts3rec_v8_6*)rec));
          break;

        case 7:
          return (fts3rec_pdu_v8_7_encode(enc, (struct fts3rec_v8_7*)rec));
          break;

        case 8:
          return (fts3rec_pdu_v8_8_encode(enc, (struct fts3rec_v8_8*)rec));
          break;

        case 9:
          return (fts3rec_pdu_v8_9_encode(enc, (struct fts3rec_v8_9*)rec));
          break;

        case 10:
          return (fts3rec_pdu_v8_10_encode(enc, (struct fts3rec_v8_10*)rec));
          break;

        case 11:
          return (fts3rec_pdu_v8_11_encode(enc, (struct fts3rec_v8_11*)rec));
          break;

        case 12:
          return (fts3rec_pdu_v8_12_encode(enc, (struct fts3rec_v8_12*)rec));
          break;

        case 13:
          return (fts3rec_pdu_v8_13_encode(enc, (struct fts3rec_v8_13*)rec));
          break;

        case 14:
          return (fts3rec_pdu_v8_14_encode(enc, (struct fts3rec_v8_14*)rec));
          break;

      }
      break;

  }

  return -1;

}
