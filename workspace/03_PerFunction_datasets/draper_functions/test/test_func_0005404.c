isPressed(const SDL_Event& event) {

  if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_KEYDOWN) return true;
  if (event.type == SDL_JOYAXISMOTION) return event.jaxis.value / initialSensitivity;
  return false;
}
