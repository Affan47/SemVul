CheckEuler( int V, int E, int F )
{
   if ( check )
      std::cerr << "Checks: V, E, F = " << V << " " << E
		<< " " << F << ":\t";

   if ( (V - E + F) != 2 )
      std::cerr << "Checks: V-E+F != 2\n" ;
   else if ( check )
      std::cerr << "V-E+F = 2\t" ;


   if ( F != (2 * V - 4) )
      std::cerr << "Checks: F=" << F
		<< " != 2V-4=" << 2*V-4
		<< "; V=" << V << std::endl;
   else if ( check )
      std::cerr << "F = 2V-4\t" ;

   if ( (2 * E) != (3 * F) )
      std::cerr << "Checks: 2E=" << 2*E
		<< " != 3F=" << 3*F
		<< "; E=" << E
		<< ", F=" << F << std::endl;
   else if ( check )
      std::cerr << "2E = 3F\n" ;
}
