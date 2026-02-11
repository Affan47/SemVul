createUnitCostList()
{
   cout << "name;id;unitset id;new cost E;new cost M;old cost E;old cost M\n";
   for ( int i = 0; i < vehicleTypeRepository.getNum(); ++i ) {
      VehicleType* v = vehicleTypeRepository.getObject_byPos(i);
      Resources oldc = v->calcProductionCost();
      Resources newc = v->calcProductionCost();

      cout <<  v->getName() << ";" << v->id << ";" << getUnitSetID( v) << ";" << newc.energy << ";" << newc.material << ";" << oldc.energy << ";" << oldc.material << "\n";
   }
}
