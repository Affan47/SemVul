find_right_tangent(point_cloud *cloud, point *reference) {
  cloud_size_t start = 0;
  cloud_size_t end = cloud->size;

  turn_t start_prev = turn(*reference, cloud->points[start], cloud->points[end - 1]);
  turn_t start_next = turn(*reference, cloud->points[start], cloud->points[(start + 1) % end]);

  while (start < end) {
    cloud_size_t pivot = (start + end) / 2;
    turn_t pivot_prev = turn(*reference, cloud->points[pivot], cloud->points[(pivot - 1) % cloud->size]);
    turn_t pivot_next = turn(*reference, cloud->points[pivot], cloud->points[(pivot + 1) % cloud->size]);

    turn_t pivot_side = turn(*reference, cloud->points[start], cloud->points[pivot]);

    if ((pivot_prev != TURN_RIGHT) && (pivot_next != TURN_RIGHT)) {
      start = pivot;
      break;
    } else if ((pivot_side == TURN_LEFT && start_next == TURN_RIGHT) || (start_prev == start_next) || (pivot_side == TURN_RIGHT && pivot_prev == TURN_RIGHT)) {
      end = pivot;
    } else {
      start = pivot + 1;
      start_prev = (turn_t) - pivot_next;
      start_next = turn(*reference, cloud->points[start], cloud->points[(start + 1) % cloud->size]);
    }
  }

  if (!compare_point(&cloud->points[start], reference)) {
    start = (start + 1) % cloud->size;
  }

  return &cloud->points[start];
}
