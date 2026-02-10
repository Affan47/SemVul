wdata_check(writer_data_t* data)
{
  queue* elem, *tmp;
  double center_lat, center_lon;

  if ((data->ct <= WAYPOINTS_PER_BLOCK) ||


      ((data->bds.min_lat >= data->bds.max_lat) && (data->bds.min_lon >= data->bds.max_lon))) {
    if (data->ct > 1) {
      sortqueue(&data->Q, compare_wpt_cb);
    }
    return;
  }


  center_lat = center_lon = 0;
  QUEUE_FOR_EACH(&data->Q, elem, tmp) {
    waypoint* wpt = (waypoint*) elem;
    center_lat += wpt->latitude;
    center_lon += wpt->longitude;
  }
  center_lat /= data->ct;
  center_lon /= data->ct;

  QUEUE_FOR_EACH(&data->Q, elem, tmp) {
    waypoint* wpt = (waypoint*) elem;
    writer_data_t** ref;

    if (wpt->latitude < center_lat) {
      if (wpt->longitude < center_lon) {
        ref = &data->buttom_left;
      } else {
        ref = &data->buttom_right;
      }
    } else {
      if (wpt->longitude < center_lon) {
        ref = &data->top_left;
      } else {
        ref = &data->top_right;
      }
    }

    if (*ref == NULL) {
      *ref = wdata_alloc();
    }

    data->ct--;
    dequeue(&wpt->Q);

    wdata_add_wpt(*ref, wpt);
  }

  if (data->top_left) {
    wdata_check(data->top_left);
  }
  if (data->top_right) {
    wdata_check(data->top_right);
  }
  if (data->buttom_left) {
    wdata_check(data->buttom_left);
  }
  if (data->buttom_right) {
    wdata_check(data->buttom_right);
  }
}
