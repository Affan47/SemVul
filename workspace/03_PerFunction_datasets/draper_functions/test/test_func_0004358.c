copy (Population population, unsigned dest, unsigned src)
{
  if (population.person[src].length == population.person[dest].length)
    {
      population.person[dest].width = population.person[src].width;
      population.person[dest].length = population.person[src].length;
      population.person[dest].penalty_sum =
	population.person[src].penalty_sum;

      memcpy (population.person[dest].gene, population.person[src].gene,
	      population.person[src].length);
    }
}
