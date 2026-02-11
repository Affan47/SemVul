IterateDirtyRegions(
    uint32_t marks,
    Address area_start,
    Address area_end,
    DirtyRegionCallback visit_dirty_region,
    ObjectSlotCallback copy_object_func) {
  uint32_t newmarks = 0;
  uint32_t mask = 1;

  if (area_start >= area_end) {
    return newmarks;
  }

  Address region_start = area_start;


  Address second_region =
      reinterpret_cast<Address>(
          reinterpret_cast<intptr_t>(area_start + Page::kRegionSize) &
          ~Page::kRegionAlignmentMask);


  Address region_end = Min(second_region, area_end);

  if (marks & mask) {
    if (visit_dirty_region(region_start, region_end, copy_object_func)) {
      newmarks |= mask;
    }
  }
  mask <<= 1;


  region_start = region_end;
  region_end = region_start + Page::kRegionSize;

  while (region_end <= area_end) {
    if (marks & mask) {
      if (visit_dirty_region(region_start, region_end, copy_object_func)) {
        newmarks |= mask;
      }
    }

    region_start = region_end;
    region_end = region_start + Page::kRegionSize;

    mask <<= 1;
  }

  if (region_start != area_end) {


    if (marks & mask) {
      if (visit_dirty_region(region_start, area_end, copy_object_func)) {
        newmarks |= mask;
      }
    }
  }

  return newmarks;
}
