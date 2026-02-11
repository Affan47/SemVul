Free_Road_Changes(void)
{
  int i = 0;
  if (roadchanges) {
    while (roadchanges[i].name) {
      xfree(roadchanges[i].name);
      i++;
    }
    xfree(roadchanges);
  }
  roadchanges = NULL;
}
