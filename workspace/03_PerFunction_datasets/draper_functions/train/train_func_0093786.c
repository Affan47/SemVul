set(int day, double start, double end) {
    if (day < 0 || day > 6) return;
    days[day].present = true;
    days[day].start_hour = start;
    days[day].end_hour = end;
}
