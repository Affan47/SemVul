rotateRight(double rotationEnergyNeed,double rotationSpeed)
{
   if(energy>rotationEnergyNeed)
   {
      energy-=rotationEnergyNeed;
      setRotation(rotation-rotationSpeed);
   }
}
