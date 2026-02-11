convex_hull_graham_scan(point_cloud *cloud, point_cloud *hull) {
  qsort(cloud->points, cloud->size, sizeof(point), &compare_point);

  init_point_cloud(hull, 0, cloud->size + 1);

  for (cloud_size_t k = 0; k < cloud->size; k++) {
    update_hull(hull, cloud->points[k]);
  }


  for (cloud_size_t k = cloud->size ; k > 0; k--) {
    update_hull(hull, cloud->points[k-1]);
  }


  pop(hull);
}
