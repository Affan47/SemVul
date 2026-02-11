deflate_common()
{untested();
  unreachable();
  if (has_common()) {untested();
    COMMON_COMPONENT* deflated_common = mutable_common()->deflate();
    if (deflated_common != common()) {untested();
      attach_common(deflated_common);
    }else{untested();
    }
  }else{untested();
    unreachable();
  }
}
