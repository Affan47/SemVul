eventKeyDown(const SDL_KeyboardEvent* key)
{
   int mod = SDL_GetModState() & ~(KMOD_NUM | KMOD_CAPS | KMOD_MODE);
   if ( mod )
      return false;

   switch ( key->keysym.sym ) {
      case SDLK_ESCAPE:
         closeWindow();
         return true;

      case SDLK_PLUS:
         addProductionLine();
         QuitModal();
         return true;

      case SDLK_MINUS:
         removeProductionLine();
         QuitModal();
         return true;
         default:;
   }

   return false;
}
