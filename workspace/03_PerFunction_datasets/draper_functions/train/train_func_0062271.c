setSelected(int index, bool value, bool toggle)
{
  if ( selected == NULL ) {
    return;
  }

  if ( index < 0 || index >= nofElements ) {
    return;
  }


  if ( toggle ) {
    selected[index] = !selected[index];


  } else {
    selected[index] = value;
  }

}
