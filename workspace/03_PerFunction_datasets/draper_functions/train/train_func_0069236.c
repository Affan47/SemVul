check_marks(struct area *area, long index)
{
    int result = 0;

    if (check_startmark(area->area) != index) {
        error(0, "Start marker was damaged for area %ld", index);
        result = -1;
    }
    if (check_endmark(area->area, area->area_size) < 0) {
        error(0, "End marker was damaged for area %ld", index);
        result = -1;
    }

    return result;
}
