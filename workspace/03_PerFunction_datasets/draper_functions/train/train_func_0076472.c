s48_when_keyboard_interrupt(int ign)
{
  keyboard_interrupt_count += 1;
  NOTE_EVENT;
  return;
}
