go ( const Context& context )
{
   MapCoordinate targetPosition;

   if ( getState() != SetUp )
      return ActionResult(22000);

   if ( !avail( getUnit() ) )
      return ActionResult(21506);

   searchFields();

   vector<int>* objects;
   if ( mode == Build ) {
      objects = &objectsCreatable[target];
   } else {
      objects = &objectsRemovable[target];
   }

   if ( find( objects->begin(), objects->end(), object ) == objects->end() )
      return ActionResult( 21507 );


   ObjectType* obj = getMap()->getobjecttype_byid( object );

   RecalculateAreaView rav ( getMap(), target, maxViewRange / maxmalq + 1, &context );


   bool objectAffectsVisibility = obj->basicjamming_plus || obj->viewbonus_plus || obj->viewbonus_abs != -1 || obj->basicjamming_abs != -1;
   if ( objectAffectsVisibility )
      rav.removeView();

   ActionResult res(0);
   if ( mode == Build )
      res = (new SpawnObject(getMap(), target, object ))->execute( context );
   else
      res = (new RemoveObject(getMap(), target, object ))->execute( context );


   if ( objectAffectsVisibility )
      rav.addView();

   if ( res.successful() )
      res = (new ConsumeResource( getUnit(), mode==Build ? obj->buildcost : obj->removecost ))->execute(context);

   if ( res.successful() )
      res = (new ChangeUnitMovement( getUnit(), mode==Build ? obj->build_movecost : obj->remove_movecost, true ))->execute(context);

   if ( res.successful() ) {
      if ( context.display )
         context.display->repaintDisplay();
      setState( Finished );
   } else
      setState( Failed );
   return res;

}
