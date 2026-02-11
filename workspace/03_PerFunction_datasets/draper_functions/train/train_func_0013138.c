ifile_concise_ratings (char * path, FILE * FP, category_rating * ratings,
                     ifile_db * idata, int thresh)
{

  float diff=0;

  diff=thresh+1;

  if (thresh != 0 &&
      idata->num_folders > 1 &&
      (ratings[0].rating + ratings[1].rating) != 0)
  {
    diff = -(ratings[0].rating - ratings[1].rating) /
                  (ratings[0].rating + ratings[1].rating) * 1000;
  }
  if (path) fprintf (FP, "%s ", path);
  if (diff < thresh)
    fprintf (FP, "%s,%s\n", ratings[0].category, ratings[1].category);
  else
    fprintf (FP, "%s\n", ratings[0].category);
}
