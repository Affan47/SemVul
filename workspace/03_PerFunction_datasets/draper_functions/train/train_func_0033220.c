set_names( const char *storyname )
{
   char *per_pos = 0;

   strcpy( save_name, storyname );
   strcpy( script_name, storyname );
   strcpy( record_name, storyname );
   strcpy( auxilary_name, storyname );


   per_pos = strrchr( storyname, '.' );
   if ( per_pos )
   {
      per_pos = strrchr( save_name, '.' );
      *( per_pos ) = '\0';
      strcat( save_name, ".sav" );

      per_pos = strrchr( script_name, '.' );
      *( per_pos ) = '\0';
      strcat( script_name, ".scr" );

      per_pos = strrchr( record_name, '.' );
      *( per_pos ) = '\0';
      strcat( record_name, ".rec" );

      per_pos = strrchr( auxilary_name, '.' );
      *( per_pos ) = '\0';
      strcat( auxilary_name, ".aux" );
   }
   else
   {
      strcat( save_name, ".sav" );
      strcat( script_name, ".src" );
      strcat( record_name, ".rec" );
      strcat( auxilary_name, ".aux" );
   }
}
