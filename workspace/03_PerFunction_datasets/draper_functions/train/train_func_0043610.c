vmpressure_calc_level(unsigned long scanned,
						    unsigned long reclaimed)
{
	unsigned long scale = scanned + reclaimed;
	unsigned long pressure = 0;


	if (reclaimed >= scanned)
		goto out;


	pressure = scale - (reclaimed * scale / scanned);
	pressure = pressure * 100 / scale;

out:
	pr_debug("%s: %3lu  (s: %lu  r: %lu)\n", __func__, pressure,
		 scanned, reclaimed);

	return vmpressure_level(pressure);
}
