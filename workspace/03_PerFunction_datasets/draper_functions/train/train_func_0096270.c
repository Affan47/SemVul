HTMLFrame(li, env, p)
HTMLInfo li;
HTMLEnv env;
MLElement p;
{
  HTMLFrameInfo fi;
  char *url;
  ChimeraRequest *wr;
  HTMLFrameSetInfo fset;
  unsigned int size;

  fset = (HTMLFrameSetInfo)env->closure;

  if ((url = MLFindAttribute(p, "src")) == NULL) return;

  if ((wr = RequestCreate(li->cres, url, li->burl)) == NULL) return;

  fi = (HTMLFrameInfo)MPCGet(li->mp, sizeof(struct HTMLFrameInfoP));

  fi->li = li;
  fi->wr = wr;

  fi->box = HTMLCreateBox(li, env);
  fi->box->destroy = DestroyIFrame;
  fi->box->closure = fi;
  fi->x = fset->x;
  fi->y = fset->y;
  fi->name = MLFindAttribute(p, "name");
  fi->fset = fset;

  if (fset->current_size == NULL) size = LASTRESORTSIZE;
  else size = fset->current_size->size;

  if (fset->horiz)
  {
    fi->width = size;
    fi->height = fset->other_size;
    fset->x += size;
  }
  else
  {
    fi->width = fset->other_size;
    fi->height = size;
    fset->y += size;
  }

  GListAddHead(fset->frames, fi);

  fset->current_size = (HTMLFrameSize)GListGetNext(fset->sizes);

  return;
}
