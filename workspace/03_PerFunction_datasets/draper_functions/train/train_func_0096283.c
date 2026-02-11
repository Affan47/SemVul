RecordPosition(int position) {
  if (!FLAG_debug_info || position == RelocInfo::kNoPosition) return;
  masm()->positions_recorder()->RecordPosition(position);
}
