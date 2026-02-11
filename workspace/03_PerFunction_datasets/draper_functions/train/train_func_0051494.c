AvailableProductionItemFactory(  ContainerBase* container_, ContainerBase::Production& prod )  : container( container_ ), selectedItem(NULL), production( prod )
      {
         restart();
      }
