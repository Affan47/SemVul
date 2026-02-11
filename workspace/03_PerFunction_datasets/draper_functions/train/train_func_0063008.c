rtp_stats_set_bandwidths (RTPSessionStats * stats, guint rtp_bw,
    gdouble rtcp_bw, guint rs, guint rr)
{
  GST_DEBUG ("recalc bandwidths: RTP %u, RTCP %f, RS %u, RR %u", rtp_bw,
      rtcp_bw, rs, rr);


  if (rs != -1 && rr != -1)
    rtcp_bw = rs + rr;


  if (rtcp_bw > 0.0 && rtcp_bw < 1.0) {
    if (rtp_bw > 0.0)
      rtcp_bw = rtp_bw * rtcp_bw;
    else
      rtcp_bw = -1.0;
  }


  if (rtp_bw == -1 && rtcp_bw > 1.0)
    rtp_bw = rtcp_bw * 20;
  else if (rtp_bw != -1 && rtcp_bw < 0.0)
    rtcp_bw = rtp_bw / 20;
  else if (rtp_bw == -1 && rtcp_bw < 0.0) {

    rtp_bw = RTP_STATS_BANDWIDTH;
    rtcp_bw = rtp_bw * RTP_STATS_RTCP_FRACTION;
  }

  stats->bandwidth = rtp_bw;
  stats->rtcp_bandwidth = rtcp_bw;


  if (rs == -1) {

    if (rr == -1) {

      rs = stats->rtcp_bandwidth * RTP_STATS_SENDER_FRACTION;
      rr = stats->rtcp_bandwidth * RTP_STATS_RECEIVER_FRACTION;
    } else {

      if (stats->rtcp_bandwidth > rr)
        rs = stats->rtcp_bandwidth - rr;
      else
        rs = 0;
    }
  } else if (rr == -1) {

    if (stats->rtcp_bandwidth > rs)
      rr = stats->rtcp_bandwidth - rs;
    else
      rr = 0;
  }

  if (stats->rtcp_bandwidth > 0) {
    stats->sender_fraction = ((gdouble) rs) / ((gdouble) stats->rtcp_bandwidth);
    stats->receiver_fraction = 1.0 - stats->sender_fraction;
  } else {

    stats->sender_fraction = 0.0;
    stats->receiver_fraction = 0.0;
  }
  GST_DEBUG ("bandwidths: RTP %u, RTCP %u, RS %f, RR %f", stats->bandwidth,
      stats->rtcp_bandwidth, stats->sender_fraction, stats->receiver_fraction);
}
