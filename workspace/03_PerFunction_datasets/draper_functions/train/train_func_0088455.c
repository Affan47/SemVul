Curl_speedcheck(struct SessionHandle *data,
                         struct timeval now)
{
  if((data->progress.current_speed >= 0) &&
     data->set.low_speed_time &&
     (Curl_tvlong(data->state.keeps_speed) != 0) &&
     (data->progress.current_speed < data->set.low_speed_limit)) {
    long howlong = Curl_tvdiff(now, data->state.keeps_speed);


    if( (howlong/1000) > data->set.low_speed_time) {

      failf(data,
            "Operation too slow. "
            "Less than %d bytes/sec transfered the last %d seconds",
            data->set.low_speed_limit,
            data->set.low_speed_time);
      return CURLE_OPERATION_TIMEOUTED;
    }
    Curl_expire(data, howlong);
  }
  else {

    data->state.keeps_speed = now;

    if(data->set.low_speed_limit)


      Curl_expire(data, data->set.low_speed_time*1000);
  }
  return CURLE_OK;
}
