getMax( ContainerBase* c, bool avail )
      {
         if ( avail ) {
            int needed = getResourceWatch( c ).limit().resource(resourceType) - getAvail( c );
            int av = min ( needed, getOpposingResourceWatch( c ).avail().resource(resourceType) );

            return getAvail( c ) + av;
         } else
            return getResourceWatch( c ).limit().resource(resourceType);
      }
