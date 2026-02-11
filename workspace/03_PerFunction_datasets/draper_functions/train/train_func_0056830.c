free_juggle(jugglestruct *sp) {
  if (sp->head != NULL) {
	while (sp->head->next != sp->head) {
	  trajectory_destroy(sp->head->next);
	}
	free(sp->head);
	sp->head = (Trajectory *) NULL;
  }
  if(sp->objects != NULL) {
	while (sp->objects->next != sp->objects) {
	  object_destroy(sp->objects->next);
	}
	free(sp->objects);
	sp->objects = (Object*)NULL;
  }
  if(sp->wander != NULL) {
	while (sp->wander->next != sp->wander) {
	  Wander *w = sp->wander->next;
	  REMOVE(w);
	}
	free(sp->wander);
	sp->wander = (Wander*)NULL;
  }
  if(sp->pattern != NULL) {
	free(sp->pattern);
	sp->pattern = NULL;
  }
  if (sp->mode_font!=None) {
	XFreeFontInfo(NULL,sp->mode_font,1);
	sp->mode_font = None;
  }
}
