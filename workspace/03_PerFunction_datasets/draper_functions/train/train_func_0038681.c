cam_keypoints_tracking2_matches_to_file(CamKeypointsMatches *track, char *outFile, int nb)
{
  FILE		*file;
  char		filename[256];
  int		i;
  POINTS_TYPE	tmp;

  sprintf(filename, "src/3d/data/tracking/%s%i.matches", outFile, nb);
  file = fopen(filename, "w");
  if (!file)
    {
      printf("cam_keypoints_tracking2_matches_to_file : unable to open %s\n", filename);
      exit (-1);
    }
  fwrite(&track->nbMatches, sizeof(int), 1, file);
  for (i = 0 ; i < track->nbMatches + track->nbOutliers ; ++i)
    {
	if (track->pairs[i].mark)
	  {
	    tmp = (POINTS_TYPE)track->pairs[i].p1->x;
	    fwrite(&tmp, sizeof(POINTS_TYPE), 1, file);
	    tmp = (POINTS_TYPE)track->pairs[i].p1->y;
	    fwrite(&tmp, sizeof(POINTS_TYPE), 1, file);
	    tmp = (POINTS_TYPE)track->pairs[i].p2->x;
	    fwrite(&tmp, sizeof(POINTS_TYPE), 1, file);
	    tmp = (POINTS_TYPE)track->pairs[i].p2->y;
	    fwrite(&tmp, sizeof(POINTS_TYPE), 1, file);
	  }
    }
  fclose(file);
}
