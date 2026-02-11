GenerateNoise(const Quantum pixel,
                                   const NoiseType noise_type)
{
  double
    value;

  value=(double) pixel+GenerateDifferentialNoise(pixel,noise_type,
						 AcquireMagickRandomKernel());
  return (RoundDoubleToQuantum(value));
}
